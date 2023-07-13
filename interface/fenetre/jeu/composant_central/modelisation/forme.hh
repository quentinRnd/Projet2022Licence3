#ifndef FORME_H
#define FORME_H

#include "coordonnee.hh"

// Modélise des formes
namespace Forme
{
	// Constantes numériques calculés
	namespace Constantes
	{
		// Détermine la finesse de résolution angulaire des modéliasations
		extern const Coordonnee::Angle resolution_angulaire;
	};

	// Formes de dimension 2
	namespace Dimension_2
	{
		// Modélise un carré
		void rectangle
		(			
			Coordonnee::Distance const & taille_x,
			Coordonnee::Distance const & taille_y
		);

		// Modélise un rectangle texturé
		void rectangle_texture
		(
			Coordonnee::Distance const & taille_x,
			Coordonnee::Distance const & taille_y,
			GLuint const & texture,
			std::vector<GLint> const & parametres = {GL_MODULATE}
		);

		// Modélise un disque
		void disque
		(
			Coordonnee::Distance const & diametre_exterieur_xy,
			Coordonnee::Distance  const & diametre_interieur_xy = 0,
			GLenum const & face_visible = GL_FRONT,
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_rayon_xy = {-180, 180}
		);

		// Modélise un disque texturé
		void disque_texture
		(
			Coordonnee::Distance const & diametre_exterieur_xy,
			GLuint const & texture,
			std::vector<GLint> const & parametres = {GL_MODULATE},
			Coordonnee::Distance  const & diametre_interieur_xy = 0,
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_rayon_xy = {-180, 180}
		);
	}

	// Formes de dimension 3
	namespace Dimension_3
	{
		// Modélise un pavé
		void pave
		(
			std::array<Coordonnee::Distance, 3> const & taille_xyz
		);

		// Modélise un pavé texturé
		void pave_texture
		(
			std::array<Coordonnee::Distance, 3> const & taille_xyz,
			GLuint const & texture,
			std::vector<GLint> const & parametres = {GL_MODULATE}
		);

		// Modélise une sphère
		void sphere
		(
			Coordonnee::Distance const & diametre_xyz,
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_rayon_z = {-90, 90},
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_rayon_xy = {-180, 180}
		);

		void sphere_texture
		(
			Coordonnee::Distance const & diametre_xyz,
			GLuint const & texture,
			std::vector<GLint> const & parametres = {GL_MODULATE},
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_rayon_z = {-90, 90},
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_rayon_xy = {-180, 180}
		);

		// Modélise une tore
		void tore
		(
			Coordonnee::Distance const & diametre_tore_xy,
			Coordonnee::Distance const & diametre_tube_yz,
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_tore_xy = {-180, 180},
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_tube_yz = {-180, 180}
		);

		// Modélise une texturé
		void tore_texture
		(
			Coordonnee::Distance const & diametre_tore_xy,
			Coordonnee::Distance const & diametre_tube_yz,
			GLuint const & texture,
			std::vector<GLint> const & parametres = {GL_MODULATE},
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_tore_xy = {-180, 180},
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_tube_yz = {-180, 180}
		);

		// Modélise un cylindre circulaire droit
		void tube
		(
			Coordonnee::Distance const & diametre_xy,
			Coordonnee::Distance const & taille_z,
			GLenum const & surface_visible = GL_FRONT,
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_rayon_xy = {-180, 180}
		);

		// Modélise un cylindre circulaire droit texturé
		void tube_texture
		(
			Coordonnee::Distance const & diametre_xy,
			Coordonnee::Distance const & taille_z,
			GLuint const & texture,
			std::vector<GLint> const & parametres = {GL_MODULATE},
			std::pair<Coordonnee::Angle, Coordonnee::Angle> const & interval_rayon_xy = {-180, 180}
		);
	}
}

#endif // FORME_H
