#include "arbre.hh"

#include "../../../forme.hh"
#include "../../../texture.hh"

Arbre::Arbre
(
	std::array<Coordonnee::Distance, 3> const & position_xyz,
	std::array<Coordonnee::Angle, 3> const & orientation_xyz,
	Coordonnee::Distance const & diametre_xz_tronc,
	Coordonnee::Distance const & taille_y_tronc,
	Coordonnee::Distance const & diametre_xyz_feuilles
):
	Objet_unique(position_xyz, orientation_xyz),
	_diametre_xz_tronc(diametre_xz_tronc),
	_taille_y_tronc(taille_y_tronc),
	_diametre_xyz_feuilles(diametre_xyz_feuilles)
{}

Coordonnee::Distance const & Arbre::diametre_xz_tronc() const
{
	return _diametre_xz_tronc;
}

Coordonnee::Distance const & Arbre::taille_y_tronc() const
{
	return _taille_y_tronc;
}

Coordonnee::Distance const & Arbre::diametre_xyz_feuilles() const
{
	return _diametre_xyz_feuilles;
}

void Arbre::contenu_liste()
{
	// Positionne l'arbre au dessus de l'origine en y
	glTranslated(0, (_taille_y_tronc + _diametre_xyz_feuilles / 2) / 2, 0);

	glPushMatrix();
	{
		glRotated(90, 1, 0, 0);

		// Modélise le tronc de l'arbre
		Forme::Dimension_3::tube_texture(_diametre_xz_tronc, _taille_y_tronc + _diametre_xyz_feuilles / 2, Texture::Niveau::tronc);
	}
	glPopMatrix();

	glTranslated(0, (_taille_y_tronc + _diametre_xyz_feuilles / 2) / 2, 0);

	// Modélise les feuilles de l'arbre
	Forme::Dimension_3::sphere_texture(_diametre_xyz_feuilles, Texture::Niveau::feuilles);
}
