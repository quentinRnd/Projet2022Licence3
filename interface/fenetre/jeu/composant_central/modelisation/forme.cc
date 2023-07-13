#include "forme.hh"

#include <cmath>
#include <utility>

namespace Forme
{
	namespace Constantes
	{
		const Coordonnee::Angle resolution_angulaire(1);
	}

	// Calcule et renvoie la normale d'une surface représenté par un triangle
	std::array<Coordonnee::Distance, 3> calcule_normale
	(
		std::array<std::array<Coordonnee::Distance, 3>, 3> const & triangle
	)
	{
		// Détermine l'angle du deuxième point du triangle déterminé par 2 vecteurs
		const std::array<std::array<Coordonnee::Distance, 3>, 2> vecteurs
		({
			 std::array<Coordonnee::Distance, 3> {triangle[2][0] - triangle[1][0], triangle[2][1] - triangle[1][1], triangle[2][2] - triangle[1][2]},
			 std::array<Coordonnee::Distance, 3> {triangle[0][0] - triangle[1][0], triangle[0][1] - triangle[1][1], triangle[0][2] - triangle[1][2]}
		 });

		// La normale est le produit cartésient des 2 vecteurs
		std::array<Coordonnee::Distance, 3> normale
		({
			(vecteurs[0][1] * vecteurs[1][2]) - (vecteurs[0][2] * vecteurs[1][1]),
			(vecteurs[0][2] * vecteurs[1][0]) - (vecteurs[0][0] * vecteurs[1][2]),
			(vecteurs[0][0] * vecteurs[1][1]) - (vecteurs[0][1] * vecteurs[1][0])
		});

		// Calcule la norme de la normale
		const Coordonnee::Distance norme
		(sqrtf(
			normale[0] * normale[0] +
			normale[1] * normale[1] +
			normale[2] * normale[2]
		));

		// Normalise la normale (norme de 1)
		normale = std::array<Coordonnee::Distance, 3>
		({
			normale[0] / norme,
			normale[1] / norme,
			normale[2] / norme
		});

		// Renvoie la normale
		return normale;
	}

	// Calcul et défini la normale courante d'une surface représenté par un triangle
	void applique_normale
	(
		std::array<std::array<Coordonnee::Distance, 3>, 3> const & triangle
	)
	{
		// Défini la normale courante
		const std::array<Coordonnee::Distance, 3> normale(calcule_normale(triangle));
		glNormal3dv(normale.data());
	}

	namespace Dimension_2
	{
		// Modélise une bande de triangles
		void bande_triangles
		(
			std::vector<std::array<Coordonnee::Distance, 3>> const & positions
		)
		{
			// Modélise la bande de triangles
			glBegin(GL_TRIANGLE_STRIP);
			{
				// Applique la normale de la bande de triangles
				applique_normale({positions[0], positions[1], positions[2]});

				for (std::array<Coordonnee::Distance, 3> const & position: positions)
				{
					glVertex3dv(position.data());
				}
			}
			glEnd();
		}

		// Modélise un rectangle à partir de ses 4 sommets de la face avant
		void rectangle
		(
			std::array<std::array<Coordonnee::Distance, 3>, 4> sommets_face_avant,
			GLenum const & face_visible
		)
		{
			// Inverse le sommet 2 et 3 pour modéliser la face arrière du rectangle
			if (face_visible == GL_BACK)
			{
				std::swap(sommets_face_avant[1], sommets_face_avant[2]);
			}

			// Modélise la bonne face du rectangle
			Dimension_2::bande_triangles
			(
				{sommets_face_avant.begin(), sommets_face_avant.end()}
			);
		}

		void rectangle
		(
			Coordonnee::Distance const & taille_x,
			Coordonnee::Distance const & taille_y
		)
		{
			// Calcul la moitié de la taille x et y
			const Coordonnee::Distance moitie_x(taille_x / 2);
			const Coordonnee::Distance moitie_y(taille_y / 2);

			// Modélise le rectangle
			Dimension_2::bande_triangles
			(
				{
					{moitie_x,	moitie_y,	0},
					{-moitie_x,	moitie_y,	0},
					{moitie_x,	-moitie_y,	0},
					{-moitie_x,	-moitie_y,	0}
				}
			);
		}

		void rectangle_texture
		(
			Coordonnee::Distance const & taille_x,
			Coordonnee::Distance const & taille_y,
			GLuint const & texture,
			std::vector<GLint> const & parametres
		)
		{
			// Calcul la moitié de la taille x et y
			const Coordonnee::Distance moitie_x(taille_x / 2);
			const Coordonnee::Distance moitie_y(taille_y / 2);

			// Applique la texture une surface
			glEnable(GL_TEXTURE_2D);
			{
				// Paramètre la texture
				glTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, parametres.data());

				// Attache la texture à une cible 2D
				glBindTexture(GL_TEXTURE_2D, texture);

				// Modélise le rectangle texturé
				glBegin(GL_TRIANGLE_STRIP);
				{
					glTexCoord2d(0, 0);
					glVertex3d(-moitie_x,	-moitie_y,	0);

					glTexCoord2d(1, 0);
					glVertex3d(moitie_x,	-moitie_y,	0);

					glTexCoord2d(0, 1);
					glVertex3d(-moitie_x,	moitie_y,	0);

					glTexCoord2d(1, 1);
					glVertex3d(moitie_x,	moitie_y,	0);
				}
				glEnd();
			}
			glDisable(GL_TEXTURE_2D);
		}

		// Retourne la position d'un point d'un disque
		std::array<Coordonnee::Distance, 3> point_disque
		(
			Coordonnee::Distance rayon_xy,
			Coordonnee::Angle angle_rayon_xy
		)
		{
			return
			{
				rayon_xy * cos(angle_rayon_xy.radian()),
				rayon_xy * sin(angle_rayon_xy.radian()),
				0
			};
		}

		void disque
		(
			Coordonnee::Distance const & diametre_exterieur_xy,
			Coordonnee::Distance  const & diametre_interieur_xy,
			GLenum const & face_visible,
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_rayon_xy
		)
		{
			// Le rayon exterieur du disque fait la moitié de son diamètre
			const Coordonnee::Distance rayon_exterieur_xy(diametre_exterieur_xy / 2);

			// Le rayon interieur du disque fait la moitié de son diamètre
			const Coordonnee::Distance rayon_interieur_xy(diametre_interieur_xy / 2);

			// Modélise le disque
			for
			(
				Coordonnee::Angle angle_rayon_xy(interval_rayon_xy.first);
				angle_rayon_xy < interval_rayon_xy.second;
				angle_rayon_xy += Constantes::resolution_angulaire
			)
			{
				// Modélise un rectangle du disque
				Dimension_2::rectangle
				(
					{
						point_disque(rayon_exterieur_xy, angle_rayon_xy),
						point_disque(rayon_exterieur_xy, angle_rayon_xy + Constantes::resolution_angulaire),
						point_disque(rayon_interieur_xy, angle_rayon_xy),
						point_disque(rayon_interieur_xy, angle_rayon_xy + Constantes::resolution_angulaire)
					},
					face_visible
				);
			}
		}

		void disque_texture
		(
			Coordonnee::Distance const & diametre_exterieur_xy,
			GLuint const & texture,
			std::vector<GLint> const & parametres,
			Coordonnee::Distance  const & diametre_interieur_xy,
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_rayon_xy
		)
		{
			// Le rayon exterieur du disque fait la moitié de son diamètre
			const Coordonnee::Distance rayon_exterieur_xy(diametre_exterieur_xy / 2);

			// Le rayon interieur du disque fait la moitié de son diamètre
			const Coordonnee::Distance rayon_interieur_xy(diametre_interieur_xy / 2);

			// Applique la texture une surface
			glEnable(GL_TEXTURE_2D);
			{
				// Paramètre la texture
				glTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, parametres.data());

				// Attache la texture à une cible 2D
				glBindTexture(GL_TEXTURE_2D, texture);

				// Modélise le disque
				for
				(
					Coordonnee::Angle angle_rayon_xy(interval_rayon_xy.first);
					angle_rayon_xy < interval_rayon_xy.second;
					angle_rayon_xy += Constantes::resolution_angulaire
				)
				{
					// Modélise un rectangle texturé du disque
					glBegin(GL_TRIANGLE_STRIP);
					{
						glTexCoord2d
						(
							rayon_exterieur_xy * cos(angle_rayon_xy.radian()),
							rayon_exterieur_xy * sin(angle_rayon_xy.radian())
						);
						glVertex3dv(point_disque(rayon_exterieur_xy, angle_rayon_xy).data());

						glTexCoord2d
						(
							rayon_exterieur_xy * cos(Coordonnee::Angle(angle_rayon_xy + Constantes::resolution_angulaire).radian()),
							rayon_exterieur_xy * sin(angle_rayon_xy.radian())
						);
						glVertex3dv(point_disque(rayon_exterieur_xy, angle_rayon_xy + Constantes::resolution_angulaire).data());

						glTexCoord2d
						(
							rayon_exterieur_xy * cos(angle_rayon_xy.radian()),
							rayon_exterieur_xy * sin(Coordonnee::Angle(angle_rayon_xy + Constantes::resolution_angulaire).radian())
						);
						glVertex3dv(point_disque(rayon_interieur_xy, angle_rayon_xy).data());

						glTexCoord2d
						(
							rayon_exterieur_xy * cos(Coordonnee::Angle(angle_rayon_xy + Constantes::resolution_angulaire).radian()),
							rayon_exterieur_xy * sin(Coordonnee::Angle(angle_rayon_xy + Constantes::resolution_angulaire).radian())
						);
						glVertex3dv(point_disque(rayon_interieur_xy, angle_rayon_xy + Constantes::resolution_angulaire).data());
					}
					glEnd();
				}
			}
			glDisable(GL_TEXTURE_2D);
		}
	}

	namespace Dimension_3
	{
		void pave
		(
			std::array<Coordonnee::Distance, 3> const & taille_xyz
		)
		{
			// Modélise une paire de rectangle par symétrie sur les axes x, y et z
			for (short symetrie_plan(1); symetrie_plan >= -1; symetrie_plan -= 2)
			{
				// Axe z
				glPushMatrix();
				{
					glTranslated(0, 0, symetrie_plan * taille_xyz[2] / 2);
					Dimension_2::rectangle(taille_xyz[0], taille_xyz[1]);
				}
				glPopMatrix();

				// Axe x
				glPushMatrix();
				{
					glTranslated(symetrie_plan * taille_xyz[0] / 2, 0, 0);
					glRotated(symetrie_plan * 90, 0, 1, 0);
					Dimension_2::rectangle(taille_xyz[2], taille_xyz[1]);
				}
				glPopMatrix();

				// Axe y
				glPushMatrix();
				{
					glTranslated(0, symetrie_plan * taille_xyz[1] / 2, 0);
					glRotated(symetrie_plan * -90, 1, 0, 0);
					Dimension_2::rectangle(taille_xyz[0], taille_xyz[2]);
				}
				glPopMatrix();
			}
		}

		void pave_texture
		(
			std::array<Coordonnee::Distance, 3> const & taille_xyz,
			GLuint const & texture,
			std::vector<GLint> const & parametres
		)
		{
			// Modélise une paire de rectangle par symétrie sur les axes x, y et z
			for (short symetrie_plan(1); symetrie_plan >= -1; symetrie_plan -= 2)
			{
				// Axe z
				glPushMatrix();
				{
					glTranslated(0, 0, symetrie_plan * taille_xyz[2] / 2);
					Dimension_2::rectangle_texture(taille_xyz[0], taille_xyz[1], texture, parametres);
				}
				glPopMatrix();

				// Axe x
				glPushMatrix();
				{
					glTranslated(symetrie_plan * taille_xyz[0] / 2, 0, 0);
					glRotated(symetrie_plan * 90, 0, 1, 0);
					Dimension_2::rectangle_texture(taille_xyz[2], taille_xyz[1], texture, parametres);
				}
				glPopMatrix();

				// Axe y
				glPushMatrix();
				{
					glTranslated(0, symetrie_plan * taille_xyz[1] / 2, 0);
					glRotated(symetrie_plan * -90, 1, 0, 0);
					Dimension_2::rectangle_texture(taille_xyz[0], taille_xyz[2], texture, parametres);
				}
				glPopMatrix();
			}
		}

		// Retourne la position d'un point d'une sphere
		std::array<Coordonnee::Distance, 3> point_sphere
		(
			Coordonnee::Distance const & rayon_xyz,
			Coordonnee::Angle const & angle_rayon_z,
			Coordonnee::Angle const & angle_rayon_xy
		)
		{
			return
			{
				rayon_xyz * cos(angle_rayon_z.radian()) * cos(angle_rayon_xy.radian()),
				rayon_xyz * cos(angle_rayon_z.radian()) * sin(angle_rayon_xy.radian()),
				rayon_xyz * sin(angle_rayon_z.radian())
			};
		}

		void sphere
		(
			Coordonnee::Distance const & diametre_xyz,
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_rayon_z,
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_rayon_xy
		)
		{
			// Calcul la moitié du diamètre xyz
			const Coordonnee::Distance rayon_xyz(diametre_xyz / 2);

			// Modélise la sphère
			for
			(
				Coordonnee::Angle angle_rayon_z(interval_rayon_z.first);
				angle_rayon_z < interval_rayon_z.second;
				angle_rayon_z += Constantes::resolution_angulaire
			)
			{
				for
				(
					Coordonnee::Angle angle_rayon_xy(interval_rayon_xy.first);
					angle_rayon_xy < interval_rayon_xy.second;
					angle_rayon_xy += Constantes::resolution_angulaire
				)
				{
					// Modélise un rectangle de la sphère
					Dimension_2::bande_triangles
					(
						{
							point_sphere(rayon_xyz, angle_rayon_z,										angle_rayon_xy),
							point_sphere(rayon_xyz, angle_rayon_z,										angle_rayon_xy + Constantes::resolution_angulaire),
							point_sphere(rayon_xyz, angle_rayon_z + Constantes::resolution_angulaire,	angle_rayon_xy),
							point_sphere(rayon_xyz, angle_rayon_z + Constantes::resolution_angulaire,	angle_rayon_xy + Constantes::resolution_angulaire)
						}
					);
				}
			}
		}

		// Cartographie UV d'une position sur une texture en relation avec le point sur un sphère
		void texture_point_sphere
		(
				Coordonnee::Distance const & diametre_xyz,
				std::array<Coordonnee::Distance, 3> const & position_sphere
		)
		{
			glTexCoord2d
			(
				0.5 + (atan2(position_sphere[0] / diametre_xyz, position_sphere[2] / diametre_xyz) / (2 * M_PI)),
				0.5 + (asin(position_sphere[1] / diametre_xyz) / M_PI)
			);
		}

		void sphere_texture
		(
			Coordonnee::Distance const & diametre_xyz,
			GLuint const & texture,
			std::vector<GLint> const & parametres,
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_rayon_z,
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_rayon_xy
		)
		{
			// Calcul la moitié du diamètre xyz
			const Coordonnee::Distance rayon_xyz(diametre_xyz / 2);

			// Applique la texture une surface
			glEnable(GL_TEXTURE_2D);
			{
				// Paramètre la texture
				glTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, parametres.data());

				// Attache la texture à une cible 2D
				glBindTexture(GL_TEXTURE_2D, texture);

				// Modélise la sphère
				for
				(
					Coordonnee::Angle angle_rayon_z(interval_rayon_z.first);
					angle_rayon_z < interval_rayon_z.second;
					angle_rayon_z += Constantes::resolution_angulaire
				)
				{
					for
					(
						Coordonnee::Angle angle_rayon_xy(interval_rayon_xy.first);
						angle_rayon_xy < interval_rayon_xy.second;
						angle_rayon_xy += Constantes::resolution_angulaire
					)
					{
						// Modélise un rectangle texturé de la sphère
						glBegin(GL_TRIANGLE_STRIP);
						{
							texture_point_sphere(diametre_xyz, point_sphere(rayon_xyz, angle_rayon_z, angle_rayon_xy));
							glVertex3dv(point_sphere(rayon_xyz, angle_rayon_z, angle_rayon_xy).data());

							texture_point_sphere(diametre_xyz, point_sphere(rayon_xyz, angle_rayon_z, angle_rayon_xy + Constantes::resolution_angulaire));
							glVertex3dv(point_sphere(rayon_xyz, angle_rayon_z, angle_rayon_xy + Constantes::resolution_angulaire).data());

							texture_point_sphere(diametre_xyz, point_sphere(rayon_xyz, angle_rayon_z + Constantes::resolution_angulaire, angle_rayon_xy));
							glVertex3dv(point_sphere(rayon_xyz, angle_rayon_z + Constantes::resolution_angulaire, angle_rayon_xy).data());

							texture_point_sphere(diametre_xyz, point_sphere(rayon_xyz, angle_rayon_z + Constantes::resolution_angulaire, angle_rayon_xy + Constantes::resolution_angulaire));
							glVertex3dv(point_sphere(rayon_xyz, angle_rayon_z + Constantes::resolution_angulaire, angle_rayon_xy + Constantes::resolution_angulaire).data());
						}
						glEnd();
					}
				}
			}
			glDisable(GL_TEXTURE_2D);
		}

		// Retourne la position d'un point d'un tore
		std::array<Coordonnee::Distance, 3> point_tore
		(
			Coordonnee::Distance const & rayon_tore_xy,
			Coordonnee::Distance const & rayon_tube_yz,
			Coordonnee::Angle const & angle_tore_xy,
			Coordonnee::Angle const & angle_tube_yz
		)
		{
			return
			{
				(rayon_tore_xy + rayon_tube_yz * cos(angle_tore_xy.radian())) * cos(angle_tube_yz.radian()),
				(rayon_tore_xy + rayon_tube_yz * cos(angle_tore_xy.radian())) * sin(angle_tube_yz.radian()),
				rayon_tube_yz * sin(angle_tore_xy.radian())
			};
		}

		void tore
		(
			Coordonnee::Distance const & diametre_tore_xy,
			Coordonnee::Distance const & diametre_tube_yz,
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_tore_xy,
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_tube_yz
		)
		{
			// Calcul la moitié de diamètres xy et yz
			const Coordonnee::Distance rayon_tore_xy(diametre_tore_xy / 2);
			const Coordonnee::Distance rayon_tube_yz(diametre_tube_yz / 2);

			// Modélise le tore
			for
			(
				Coordonnee::Angle angle_tore_xy(interval_tore_xy.first);
				angle_tore_xy < interval_tore_xy.second;
				angle_tore_xy += Constantes::resolution_angulaire
			)
			{
				for
				(
					Coordonnee::Angle angle_tube_yz(interval_tube_yz.first);
					angle_tube_yz < interval_tube_yz.second;
					angle_tube_yz += Constantes::resolution_angulaire
				)
				{
					// Modélise un rectangle du tore
					Dimension_2::bande_triangles
					(
						{
							point_tore(rayon_tore_xy, rayon_tube_yz, angle_tore_xy,										angle_tube_yz),
							point_tore(rayon_tore_xy, rayon_tube_yz, angle_tore_xy,										angle_tube_yz + Constantes::resolution_angulaire),
							point_tore(rayon_tore_xy, rayon_tube_yz, angle_tore_xy + Constantes::resolution_angulaire,	angle_tube_yz),
							point_tore(rayon_tore_xy, rayon_tube_yz, angle_tore_xy + Constantes::resolution_angulaire,	angle_tube_yz + Constantes::resolution_angulaire)
						}
					);
				}
			}
		}

		void tore_texture
		(
			Coordonnee::Distance const & diametre_tore_xy,
			Coordonnee::Distance const & diametre_tube_yz,
			GLuint const & texture,
			std::vector<GLint> const & parametres,
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_tore_xy,
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_tube_yz
		)
		{
			// Calcul la moitié de diamètres xy et yz
			const Coordonnee::Distance rayon_tore_xy(diametre_tore_xy / 2);
			const Coordonnee::Distance rayon_tube_yz(diametre_tube_yz / 2);

			// Applique la texture une surface
			glEnable(GL_TEXTURE_2D);
			{
				// Paramètre la texture
				glTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, parametres.data());

				// Attache la texture à une cible 2D
				glBindTexture(GL_TEXTURE_2D, texture);

				// Modélise le tore
				for
				(
					Coordonnee::Angle angle_tore_xy(interval_tore_xy.first);
					angle_tore_xy < interval_tore_xy.second;
					angle_tore_xy += Constantes::resolution_angulaire
				)
				{
					for
					(
						Coordonnee::Angle angle_tube_yz(interval_tube_yz.first);
						angle_tube_yz < interval_tube_yz.second;
						angle_tube_yz += Constantes::resolution_angulaire
					)
					{
						// Modélise un rectangle texturé du tore
						glBegin(GL_TRIANGLE_STRIP);
						{
							glTexCoord2d((angle_tore_xy + 180) / 360, (angle_tube_yz + 180) / 360);
							glVertex3dv(point_tore(rayon_tore_xy, rayon_tube_yz, angle_tore_xy, angle_tube_yz).data());

							glTexCoord2d((angle_tore_xy + 180) / 360, (angle_tube_yz + Constantes::resolution_angulaire + 180) / 360);
							glVertex3dv(point_tore(rayon_tore_xy, rayon_tube_yz, angle_tore_xy, angle_tube_yz + Constantes::resolution_angulaire).data());

							glTexCoord2d((angle_tore_xy + Constantes::resolution_angulaire + 180) / 360, (angle_tube_yz + 180) / 360);
							glVertex3dv(point_tore(rayon_tore_xy, rayon_tube_yz, angle_tore_xy + Constantes::resolution_angulaire,	angle_tube_yz).data());

							glTexCoord2d((angle_tore_xy + Constantes::resolution_angulaire + 180) / 360, (angle_tube_yz + Constantes::resolution_angulaire + 180) / 360);
							glVertex3dv(point_tore(rayon_tore_xy, rayon_tube_yz, angle_tore_xy + Constantes::resolution_angulaire,	angle_tube_yz + Constantes::resolution_angulaire).data());
						}
						glEnd();
					}
				}
			}
			glDisable(GL_TEXTURE_2D);
		}

		// Retourne la position d'un point d'un tube
		std::array<Coordonnee::Distance, 3> point_tube
		(
			Coordonnee::Distance const & rayon_xy,
			Coordonnee::Distance const & distance_z,
			Coordonnee::Angle const & angle_rayon_xy
		)
		{
			return
			{
				rayon_xy * cos(angle_rayon_xy.radian()),
				rayon_xy * sin(angle_rayon_xy.radian()),
				distance_z
			};
		}

		void tube
		(
			Coordonnee::Distance const & diametre_xy,
			Coordonnee::Distance const & taille_z,
			GLenum const & surface_visible,
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_rayon_xy
		)
		{
			// Calcul la moitié du diamètre xy
			const Coordonnee::Distance rayon_xy(diametre_xy / 2);

			// Calcul la moitié de la taille z
			const Coordonnee::Distance moitie_z(taille_z / 2);

			for
			(
				Coordonnee::Angle angle_rayon_xy(interval_rayon_xy.first);
				angle_rayon_xy < interval_rayon_xy.second;
				angle_rayon_xy += Constantes::resolution_angulaire
			)
			{
				// Modélise un rectangle du tube
				Dimension_2::rectangle
				(
					{
						point_tube(rayon_xy, moitie_z,	angle_rayon_xy),
						point_tube(rayon_xy, -moitie_z,	angle_rayon_xy),
						point_tube(rayon_xy, moitie_z,	angle_rayon_xy + Constantes::resolution_angulaire),
						point_tube(rayon_xy, -moitie_z,	angle_rayon_xy + Constantes::resolution_angulaire)
					},
					surface_visible
				);
			}
		}

		void tube_texture
		(
			Coordonnee::Distance const & diametre_xy,
			Coordonnee::Distance const & taille_z,
			GLuint const & texture,
			std::vector<GLint> const & parametres,
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_rayon_xy
		)
		{
			// Calcul la moitié du diamètre xy
			const Coordonnee::Distance rayon_xy(diametre_xy / 2);

			// Calcul la moitié de la taille z
			const Coordonnee::Distance moitie_z(taille_z / 2);

			// Applique la texture une surface
			glEnable(GL_TEXTURE_2D);
			{
				// Paramètre la texture
				glTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, parametres.data());

				// Attache la texture à une cible 2D
				glBindTexture(GL_TEXTURE_2D, texture);

				for
				(
					Coordonnee::Angle angle_rayon_xy(interval_rayon_xy.first);
					angle_rayon_xy < interval_rayon_xy.second;
					angle_rayon_xy += Constantes::resolution_angulaire
				)
				{
					// Modélise un rectangle texturé du tube
					glBegin(GL_TRIANGLE_STRIP);
					{
						glTexCoord2d((angle_rayon_xy + 180) / 360, 0);
						glVertex3dv(point_tube(rayon_xy, moitie_z, angle_rayon_xy).data());

						glTexCoord2d((angle_rayon_xy + 180) / 360, 1);
						glVertex3dv(point_tube(rayon_xy, -moitie_z,	angle_rayon_xy).data());

						glTexCoord2d((angle_rayon_xy + Constantes::resolution_angulaire + 180) / 360, 0);
						glVertex3dv(point_tube(rayon_xy, moitie_z, angle_rayon_xy + Constantes::resolution_angulaire).data());

						glTexCoord2d((angle_rayon_xy + Constantes::resolution_angulaire + 180) / 360, 1);
						glVertex3dv(point_tube(rayon_xy, -moitie_z,	angle_rayon_xy + Constantes::resolution_angulaire).data());
					}
					glEnd();
				}
			}
			glDisable(GL_TEXTURE_2D);
		}
	}
}
