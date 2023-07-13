#include "helice.hh"

#include "../../../forme.hh"
#include "../../../matiere.hh"

Helice::Helice
(
	std::array<Coordonnee::Distance, 3> const & position_xyz,
	std::array<Coordonnee::Angle, 3> const & orientation_xyz,
	Coordonnee::Distance const & diametre_palles_xz,
	Coordonnee::Distance const & taille_palles_y,
	Coordonnee::Distance const & taille_y
):
	Objet_unique(position_xyz, orientation_xyz),
	_diametre_palles_xz(diametre_palles_xz),
	_taille_palles_y(taille_palles_y),
	_taille_y(taille_y)
{}

Coordonnee::Distance const & Helice::diametre_palles_xz() const
{
	return _diametre_palles_xz;
};

Coordonnee::Distance const & Helice::taille_palles_y() const
{
	return _taille_palles_y;
};

Coordonnee::Distance const & Helice::taille_y() const
{
	return _taille_y;
};

void Helice::contenu_liste()
{
	// Applique la matière chrome
	Matiere::applique(Matiere::chrome);

	// Place l'hélice au dessus de l'origine
	glTranslated(0, _taille_y, 0);

	// Modélise le moyeu
	Forme::Dimension_3::sphere(_taille_palles_y, {-90, 90}, {0, 180});

	// Modélise les 4 hélices
	for (short symetrie_x(0); symetrie_x < 2; ++symetrie_x)
	{
		// Modélise le tube de la palle
		glPushMatrix();
		{
			glRotated(90, 0, symetrie_x == 1, 0);
			glScaled(1, _taille_palles_y, 1);
			Forme::Dimension_3::tube(_taille_palles_y, _diametre_palles_xz);
		}
		glPopMatrix();

		// Modélise les 2 bout du tube
		for (short symetrie_z(1); symetrie_z >= -1; symetrie_z -= 2)
		{
			glPushMatrix();
			{
				glRotated(90, 0, symetrie_x == 1, 0);
				glTranslated(0, 0, symetrie_z * _diametre_palles_xz / 2);
				glScaled(1, _taille_palles_y, 1);
				glRotated(symetrie_z * -90, 0, 1, 0);
				Forme::Dimension_3::sphere(_taille_palles_y, {-90, 90}, {-90, 90});
			}
			glPopMatrix();
		}
	}

	// Modélise l'attache de l'hélice au robot
	glTranslated(0, -_taille_y / 2, 0);
	glRotated(90, 1, 0, 0);
	Forme::Dimension_3::tube(_taille_palles_y, _taille_y);
}
