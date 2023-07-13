#include "chenille.hh"

#include <cmath>

#include "../../../forme.hh"
#include "../../../matiere.hh"

Chenille::Chenille
(
	std::array<Coordonnee::Distance, 3> const & position_xyz,
	std::array<Coordonnee::Angle, 3> const & orientation_xyz,
	Coordonnee::Distance const & taille_tube_haut_x,
	Coordonnee::Distance const & longueur_tube_milieu,
	Coordonnee::Distance const & taille_coins_xy,
	std::array<Coordonnee::Distance, 2> taille_tubes_yz
):
	Objet_unique(position_xyz, orientation_xyz),
	_taille_tube_haut_x(taille_tube_haut_x),
	_longueur_tube_milieu(longueur_tube_milieu),
	_taille_coins_xy(taille_coins_xy),
	_taille_tubes_yz(taille_tubes_yz),
	_taille_tube_milieu_xy({_longueur_tube_milieu * cos(Coordonnee::Angle(45).radian()), _longueur_tube_milieu * sin(Coordonnee::Angle(45).radian())}),
	_taille_tube_bas_x(2 * ((_taille_tube_haut_x / 2) - _taille_tube_milieu_xy[0]))
{}


Coordonnee::Distance const & Chenille::taille_tube_haut_x() const
{
	return  _taille_tube_haut_x;
};

Coordonnee::Distance const & Chenille::longueur_tube_milieu() const
{
	return  _longueur_tube_milieu;
};

Coordonnee::Distance const & Chenille::taille_coins_xy() const
{
	return  _taille_coins_xy;
};

std::array<Coordonnee::Distance, 2>  const & Chenille::taille_tubes_yz() const
{
	return  _taille_tubes_yz;
};

std::array<Coordonnee::Distance, 2> const & Chenille::taille_tube_milieu_xy() const
{
	return _taille_tube_milieu_xy;
};

Coordonnee::Distance const & Chenille::taille_tube_bas_x() const
{
	return _taille_tube_bas_x;
};

void Chenille::contenu_liste()
{
	// Applique la matière plastique gris
	Matiere::applique(Matiere::plastique_gris);

	glTranslated(0, _taille_tube_milieu_xy[1], 0);

	// Modélise une chenille par symétrie sur l'axe x
	for (short symetrie_x(1); symetrie_x >= -1; symetrie_x -= 2)
	{
		glPushMatrix();
		{
			glTranslated(symetrie_x * _taille_tube_haut_x / 4, 0, 0);

			// Modélise le tube en haut
			glPushMatrix();
			{
				glScaled(1, _taille_tubes_yz[0], _taille_tubes_yz[1]);
				glRotated(90, 0, 1, 0);
				Forme::Dimension_3::tube(1, _taille_tube_haut_x / 2);
			}
			glPopMatrix();

			glTranslated(symetrie_x * _taille_tube_haut_x / 4, -_taille_coins_xy / 2, 0);

			// Modélise le coin en haut
			glPushMatrix();
			{
				glScaled(1, 1, _taille_tubes_yz[1] / _taille_tubes_yz[0]);
				if (symetrie_x == 1)
				{
					Forme::Dimension_3::tore(_taille_coins_xy, _taille_tubes_yz[0], {0, 360}, {-45, 90});
				}
				else
				{
					Forme::Dimension_3::tore(_taille_coins_xy, _taille_tubes_yz[0], {0, 360}, {90, 225});
				}
			}
			glPopMatrix();

			glPushMatrix();
			{
				glRotated(symetrie_x * -45, 0, 0, 1);

				// Modélise le tube au milieu
				glPushMatrix();
				{
					glTranslated(symetrie_x * _taille_coins_xy / 2, -_longueur_tube_milieu / 2, 0);
					glScaled(_taille_tubes_yz[0], 1, _taille_tubes_yz[1]);
					glRotated(symetrie_x * 90, 1, 0, 0);
					Forme::Dimension_3::tube(1, _longueur_tube_milieu);
				}
				glPopMatrix();

				glTranslated(0, -_longueur_tube_milieu, 0);

				// Modélise le coin en bas
				glPushMatrix();
				{
					glScaled(1, 1, _taille_tubes_yz[1] / _taille_tubes_yz[0]);
					if (symetrie_x == 1)
					{
						Forme::Dimension_3::tore(_taille_coins_xy, _taille_tubes_yz[0], {0, 360}, {-45, 0});
					}
					else
					{
						Forme::Dimension_3::tore(_taille_coins_xy, _taille_tubes_yz[0], {0, 360}, {180, 225});
					}
				}
				glPopMatrix();

				// Modélise le tube en bas
				glPushMatrix();
				{
					glRotated(symetrie_x * 45, 0, 0, 1);
					glTranslated(symetrie_x * -_taille_tube_bas_x / 4, -_taille_coins_xy / 2, 0);
					glScaled(1, _taille_tubes_yz[0], _taille_tubes_yz[1]);
					glRotated(90, 0, 1, 0);
					Forme::Dimension_3::tube(1, _taille_tube_bas_x / 2);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
}

