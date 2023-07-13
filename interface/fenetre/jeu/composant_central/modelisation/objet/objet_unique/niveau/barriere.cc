#include "barriere.hh"

#include "../../../forme.hh"
#include "../../../texture.hh"

Barriere::Barriere
(
	std::array<Coordonnee::Distance, 3> const & position_xyz,
	std::array<Coordonnee::Angle, 3> const & orientation_xyz,
	Coordonnee::Distance const & taille_y,
	Coordonnee::Distance const & diametre_barres,
	Coordonnee::Distance const & taille_x_barres,
	std::size_t const & nombre_sections
):
	Objet_unique(position_xyz, orientation_xyz),
	_taille_y(taille_y),
	_diametre_barres(diametre_barres),
	_taille_x_barres(taille_x_barres),
	_nombre_sections(nombre_sections)
{}

Coordonnee::Distance const & Barriere::taille_y() const
{
	return _taille_y;
}

Coordonnee::Distance const &  Barriere::diametre_barres() const
{
	return _diametre_barres;
}

Coordonnee::Distance const & Barriere::taille_x_barres() const
{
	return _taille_x_barres;
}

std::size_t const & Barriere::nombre_sections() const
{
	return _nombre_sections;
}

void Barriere::contenu_liste()
{
	// Positionne la barièrre au dessus de l'origine en y et centrée en x
	glTranslated(-(_nombre_sections * _taille_x_barres) / 2, _taille_y / 2, 0);

	for (std::size_t section(0); section < _nombre_sections; ++section)
	{
		glPushMatrix();
		{
			glRotated(90, 1, 0, 0);

			// Modélise une barre verticale à droite
			Forme::Dimension_3::tube_texture(_diametre_barres, _taille_y, Texture::Niveau::barriere);
		}
		glPopMatrix();

		glTranslated(_taille_x_barres / 2, 0, 0);

		glPushMatrix();
		{
			// Modélise la première barre horizontal en bas
			Forme::Dimension_3::pave_texture({_taille_x_barres, _diametre_barres, _diametre_barres}, Texture::Niveau::barriere);

			glTranslated(0, _taille_y / 4, 0);

			// Modélise la deuxième barre horizontal en haut
			Forme::Dimension_3::pave_texture({_taille_x_barres, _diametre_barres, _diametre_barres}, Texture::Niveau::barriere);
		}
		glPopMatrix();

		glTranslated(_taille_x_barres / 2, 0, 0);
	}

	glPushMatrix();
	{
		glRotated(90, 1, 0, 0);

		// Modélise la dernière barre verticale à gauche
		Forme::Dimension_3::tube_texture(_diametre_barres, _taille_y, Texture::Niveau::barriere);
	}
	glPopMatrix();
}
