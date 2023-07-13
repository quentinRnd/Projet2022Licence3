#include "roue.hh"

#include "../../../forme.hh"
#include "../../../matiere.hh"

Roue::Roue
(
	std::array<Coordonnee::Distance, 3> const & position_xyz,
	std::array<Coordonnee::Angle, 3> const & orientation_xyz,
	Coordonnee::Distance const & diametre_xy,
	Coordonnee::Distance const & epaisseur_z
):
	Objet_unique(position_xyz, orientation_xyz),
	_diametre_xy(diametre_xy),
	_epaisseur_z(epaisseur_z)
{}

Coordonnee::Distance const & Roue::diametre_xy() const
{
	return _diametre_xy;
};

Coordonnee::Distance const & Roue::epaisseur_z() const
{
	return _epaisseur_z;
};

void Roue::contenu_liste()
{
	// Applique la matière chrome
	Matiere::applique(Matiere::chrome);

	// Modélise la face avant
	glPushMatrix();
	{
		const Coordonnee::Distance diviseur_tubes_xy(1.5);
		Coordonnee::Distance diametre_tubes_xy(_diametre_xy);
		Coordonnee::Distance epaisseur_tubes_z(_epaisseur_z / 5);

		// Modélise un tube 1
		Forme::Dimension_3::tube(diametre_tubes_xy, _epaisseur_z);

		glTranslated(0, 0, _epaisseur_z / 2);

		// Modélise un morceau de disque qui ferme le tube 1 et le tube 2
		Forme::Dimension_2::disque(diametre_tubes_xy, diametre_tubes_xy / diviseur_tubes_xy);

		glTranslated(0, 0, -epaisseur_tubes_z / 2);
		diametre_tubes_xy /= diviseur_tubes_xy;

		// Modélise un tube 2
		Forme::Dimension_3::tube(diametre_tubes_xy, epaisseur_tubes_z, GL_BACK);

		glTranslated(0, 0, -epaisseur_tubes_z / 2);

		// Modélise 4 boulons
		glPushMatrix();
		{
			// Taille de du boulon
			const Coordonnee::Distance diametre_boulon_xy(diametre_tubes_xy / 10);
			const Coordonnee::Distance epaisseur_boulon_z(epaisseur_tubes_z / 2);

			glTranslated(0, 0, epaisseur_boulon_z / 2);

			const Coordonnee::Distance rayon_boulon_tube_xy(1.25 * (diametre_tubes_xy - diametre_tubes_xy / diviseur_tubes_xy));

			for (short symetrie(1); symetrie >= -1; symetrie -= 2)
			{
				for (short choix_xy(1); choix_xy >= 0; --choix_xy)
				{
					// Modélise un boulon
					glPushMatrix();
					{
						// Positionne le boulon
						glTranslated(choix_xy * symetrie * rayon_boulon_tube_xy, !choix_xy * symetrie * rayon_boulon_tube_xy, 0);

						// Modélise le bord du boulon
						Forme::Dimension_3::tube(diametre_boulon_xy, epaisseur_boulon_z);

						// Modélise le dessus du boulon
						glTranslated(0, 0, epaisseur_boulon_z / 2);
						Forme::Dimension_2::disque(diametre_boulon_xy);
					}
					glPopMatrix();
				}
			}
		}
		glPopMatrix();

		// Modélise un morceau de disque qui ferme le tube 2 et le tube 3
		Forme::Dimension_2::disque(diametre_tubes_xy, diametre_tubes_xy / diviseur_tubes_xy);

		diametre_tubes_xy /= diviseur_tubes_xy;
		glTranslated(0, 0, -epaisseur_tubes_z / 2);

		// Modélise un tube 3
		Forme::Dimension_3::tube(diametre_tubes_xy, epaisseur_tubes_z, GL_BACK);

		glTranslated(0, 0, -epaisseur_tubes_z / 2);

		// Modélise un morceau de disque qui ferme le tube 3 et le tube 4
		Forme::Dimension_2::disque(diametre_tubes_xy, diametre_tubes_xy / diviseur_tubes_xy);

		diametre_tubes_xy /= diviseur_tubes_xy;
		glTranslated(0, 0, epaisseur_tubes_z / 2);

		// Modélise un tube 4
		Forme::Dimension_3::tube(diametre_tubes_xy, epaisseur_tubes_z);

		glTranslated(0, 0, epaisseur_tubes_z / 2);

		// Modélise un disque qui ferme le tube 4
		Forme::Dimension_2::disque(diametre_tubes_xy);
	}
	glPopMatrix();

	// Face arrière
	glPushMatrix();
	{
		glTranslated(0, 0, -_epaisseur_z / 2);
		glRotated(180, 0, 1, 0);
		Forme::Dimension_2::disque(_diametre_xy);
	}
	glPopMatrix();

	// Modélise la bague central
	{
		// Modélise le tube
		Forme::Dimension_3::tube(_diametre_xy * 1.05, _epaisseur_z / 10);

		glPushMatrix();
		{
			glTranslated(0, 0, _epaisseur_z / 20);
			Forme::Dimension_2::disque(_diametre_xy * 1.05, _diametre_xy);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslated(0, 0, -_epaisseur_z / 20);
			glRotated(180, 0, 1, 0);
			Forme::Dimension_2::disque(_diametre_xy * 1.05, _diametre_xy);
		}
		glPopMatrix();
	}
}

