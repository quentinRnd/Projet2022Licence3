#include "attache_roue.hh"

#include "../../../forme.hh"
#include "../../../matiere.hh"

Attache_roue::Attache_roue
(
	std::array<Coordonnee::Distance, 3> const & position_xyz,
	std::array<Coordonnee::Angle, 3> const & orientation_xyz,
	std::array<Coordonnee::Angle, 2> const & taille_yz,
	Coordonnee::Distance const & diametre_tubes
):
	Objet_unique(position_xyz, orientation_xyz),
	_taille_yz(taille_yz),
	_diametre_tubes(diametre_tubes)
{}

std::array<Coordonnee::Angle, 2> const & Attache_roue::taille_yz() const
{
	return _taille_yz;
};

Coordonnee::Distance const & Attache_roue::diametre_tubes() const
{
	return _diametre_tubes;
};

void Attache_roue::contenu_liste()
{
	// Applique la matière plastique rouge
	Matiere::applique(Matiere::plastique_rouge);

	// Place l'hélice en dessous de l'origine
	glTranslated(0, -_taille_yz[0] / 2, 0);

	// Modélise la première partie de l'attache de roue
	glPushMatrix();
	{
		// Tourne la première partie de l'attache de roue
		glRotated(90, 1, 0, 0);

		// Modélise la première partie de l'attache de roue par un tube
		Forme::Dimension_3::tube(_diametre_tubes, _taille_yz[0]);
	}
	glPopMatrix();

	// Positionne le reste de l'attache de roue
	glTranslated(0, -_taille_yz[0] / 2, 0);

	// Modélise la deuxième partie de l'attache de roue
	glPushMatrix();
	{
		// Modélise la deuxième partie de l'attache de roue par un morceau de sphère
		Forme::Dimension_3::sphere(_diametre_tubes, {0, 90}, {-180, 0});
	}
	glPopMatrix();

	// Modélise la troisième partie de l'attache de roue
	{
		// Positionne la troisième partie de l'attache de roue
		glTranslated(0, 0, -_taille_yz[1] / 2);

		// Modélise la troisième partie de l'attache de roue par un tube
		Forme::Dimension_3::tube(_diametre_tubes, _taille_yz[1]);
	}
}
