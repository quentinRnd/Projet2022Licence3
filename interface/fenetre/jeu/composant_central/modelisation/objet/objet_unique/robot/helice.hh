#ifndef HELICE_HH
#define HELICE_HH

#include "../../objet_unique.hh"

// Hélice d'un robot
class Helice:
	public Objet_unique
{
	public:

		// Instancie une hélice avec une position et une orientation initiale
		Helice
		(
			std::array<Coordonnee::Distance, 3> const & position_xyz,
			std::array<Coordonnee::Angle, 3> const & orientation_xyz,
			Coordonnee::Distance const & diametre_palles_xz,
			Coordonnee::Distance const & taille_palles_y,
			Coordonnee::Distance const & taille_y
		);

		// Accède aux paramètres de la modélisation
		Coordonnee::Distance const & diametre_palles_xz() const;
		Coordonnee::Distance const & taille_palles_y() const;
		Coordonnee::Distance const & taille_y() const;

		// Modélisation de l'hélice
		void contenu_liste() override;

	private:

		// Diamètre xy des palles
		Coordonnee::Distance _diametre_palles_xz;

		// Taille y des palles
		Coordonnee::Distance _taille_palles_y;

		// Taille y de l'hélice
		Coordonnee::Distance _taille_y;
};

#endif // HELICE_HH
