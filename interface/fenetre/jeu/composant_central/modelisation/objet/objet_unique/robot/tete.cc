#include "tete.hh"

#include "../../../forme.hh"
#include "../../../matiere.hh"

Tete::Tete
(
	std::array<Coordonnee::Distance, 3> const & position_xyz,
	std::array<Coordonnee::Angle, 3> const & orientation_xyz,
	std::array<Coordonnee::Angle, 3> const & taille_xyz
):
	Objet_unique(position_xyz, orientation_xyz),
	_taille_xyz(taille_xyz)
{}

std::array<Coordonnee::Angle, 3> const & Tete::taille_xyz() const
{
	return _taille_xyz;
};

void Tete::contenu_liste()
{
	// Applique la matière plastique rouge
	Matiere::applique(Matiere::plastique_rouge);

	glTranslated(0, _taille_xyz[1] / 4, 0);

	// Modélise le cou de la tête
	glPushMatrix();
	{
		glRotated(90, 1, 0, 0);
		Forme::Dimension_3::tube(_taille_xyz[0] / 3, _taille_xyz[1]);
	}
	glPopMatrix();

	glTranslated(0, _taille_xyz[1], 0);

	// Met à l'échelle la tête
	glScaled(_taille_xyz[0], _taille_xyz[1], _taille_xyz[2]);

	// Modélise le bas de la tête
	glPushMatrix();
	{
		glTranslated(0, -_taille_xyz[1] / 4, 0);
		Forme::Dimension_3::sphere(_taille_xyz[0], {-90, 90}, {-180, 0});
	}
	glPopMatrix();

	// Modélise le centre de la tête
	glPushMatrix();
	{
		glRotated(90, 1, 0, 0);
		Forme::Dimension_3::tube(_taille_xyz[0], _taille_xyz[1] / 2);
	}
	glPopMatrix();

	// Modélise le haut de la tête
	glPushMatrix();
	{
		glTranslated(0, _taille_xyz[1] / 4, 0);
		Forme::Dimension_3::sphere(_taille_xyz[0], {-90, 90}, {0, 180});
	}
	glPopMatrix();
}

