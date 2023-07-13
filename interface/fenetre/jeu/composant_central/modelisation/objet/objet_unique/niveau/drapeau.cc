#include "drapeau.hh"

#include "../../../forme.hh"
#include "../../../texture.hh"

Drapeau::Drapeau
(
	std::array<Coordonnee::Distance, 3> const & position_xyz,
	std::array<Coordonnee::Angle, 3> const & orientation_xyz,
	std::array<Coordonnee::Distance, 3> const & taille_etoffe_xyz,
	Coordonnee::Distance const & diametre_xz_hampe,
	Coordonnee::Distance const & taille_y_hampe
):
	Objet_unique(position_xyz, orientation_xyz),
	_taille_etoffe_xyz(taille_etoffe_xyz),
	_diametre_xz_hampe(diametre_xz_hampe),
	_taille_y_hampe(taille_y_hampe)
{}

std::array<Coordonnee::Distance, 3> const & Drapeau::taille_etoffe_xyz() const
{
	return _taille_etoffe_xyz;
}

Coordonnee::Distance const & Drapeau::diametre_xz_hampe() const
{
	return _diametre_xz_hampe;
}

Coordonnee::Distance const & Drapeau::taille_y_hampe() const
{
	return _taille_y_hampe;
}

void Drapeau::contenu_liste()
{
	// Positionne le drapeau au dessus de l'origine en y
	glTranslated(0, _taille_y_hampe / 2, 0);

	glPushMatrix();
	{
		glRotated(90, 1, 0, 0);

		// Modélise la hampe
		Forme::Dimension_3::tube_texture(_diametre_xz_hampe, _taille_y_hampe, Texture::Niveau::hampe);

		glTranslated(0, 0, -_taille_y_hampe / 2);

		Forme::Dimension_2::disque_texture(_diametre_xz_hampe, Texture::Niveau::hampe);
	}
	glPopMatrix();

	glTranslated((_diametre_xz_hampe + _taille_etoffe_xyz[0])/ 2, (_taille_y_hampe - _taille_etoffe_xyz[1]) / 2, 0);

	// Modélise l'étoffe
	Forme::Dimension_3::pave_texture(_taille_etoffe_xyz, Texture::Niveau::damier);

}
