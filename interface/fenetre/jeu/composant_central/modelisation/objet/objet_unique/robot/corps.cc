#include "corps.hh"

#include "../../../forme.hh"
#include "../../../matiere.hh"
#include "../../../texture.hh"

Corps::Corps
(
	std::array<Coordonnee::Distance, 3> const & position_xyz,
	std::array<Coordonnee::Angle, 3> const & orientation_xyz,
	std::array<Coordonnee::Distance, 3> const & taille_xyz
):
	Objet_unique(position_xyz, orientation_xyz),
	_taille_xyz(taille_xyz)
{}

std::array<Coordonnee::Distance, 3> const & Corps::taille_xyz() const
{
	return _taille_xyz;
};

void Corps::contenu_liste()
{
	// Applique la matière plastique rouge
	Matiere::applique(Matiere::plastique_rouge);

	// Modélise des paires identiques sur une symetrie
	for (short symetrie_1(1); symetrie_1 >= -1; symetrie_1 -= 2)
	{
		// Modélise le haut et la bas
		glPushMatrix();
		{
			// Place le haut/bas
			glTranslated(0, symetrie_1 * _taille_xyz[1] / 2, 0);

			glRotated(symetrie_1 * -90, 1, 0, 0);

			// Modélise le haut/bas par un carré
            Forme::Dimension_2::rectangle(_taille_xyz[0], _taille_xyz[2]);
		}
		glPopMatrix();

		// Modélise les cotés par des tubes
		glPushMatrix();
		{
			Coordonnee::Distance taille_x(_taille_xyz[0]);
			Coordonnee::Distance taille_z(_taille_xyz[2]);
			for (short symetrie_2(1); symetrie_2 >= -1; symetrie_2 -= 2)
			{
				glPushMatrix();
				{
					// Place le côté
					glTranslated(symetrie_1 * taille_x / 2, 0, 0);

					// Met à l'échelle le côté
					glScaled(1, _taille_xyz[1], 1);

					// Tourne le côté
					short rotations(symetrie_1 == 1);
					glRotated(rotations * 180, 0, 1, 0);

					// Modélise le côté par un demi tube
                    Forme::Dimension_3::tube(1, taille_z, Texture::Robot::coque);
				}
				glPopMatrix();

				// Passe de l'axe z à l'axe x
				glRotated(90, 0, 1, 0);
				std::swap(taille_z, taille_x);
			}
		}
		glPopMatrix();

		// Modélise les 4 coins sur les axes x et z
		for (short symetrie_2(1); symetrie_2 >= -1; symetrie_2 -= 2)
		{
			glPushMatrix();
			{
				// Place le coin
				glTranslated(symetrie_2 * _taille_xyz[0] / 2, 0, symetrie_1 * _taille_xyz[2] / 2);

				// Met à l'échelle le coin
				glScaled(1, _taille_xyz[1], 1);

				// Tourne le coin
				const short rotations((symetrie_1 == -1) + (symetrie_2 == -1) + 2 * (symetrie_1 == 1) * (symetrie_2 == -1));
				glRotated(rotations * 90, 0, 1, 0);

				// Modélise le coin par un morceau de sphère
                Forme::Dimension_3::sphere(1,{0, 90}, {-90, 90});
			}
			glPopMatrix();
		}
	}
}
