#ifndef TETE_HH
#define TETE_HH

#include "../../objet_unique.hh"

// Tête d'un robot
class Tete:
	public Objet_unique
{
	public:

		// Instancie une tete avec une position et une orientation initiale
		Tete
		(
			std::array<Coordonnee::Distance, 3> const & position_xyz,
			std::array<Coordonnee::Angle, 3> const & orientation_xyz,
			std::array<Coordonnee::Angle, 3> const & taille_xyz
		);

		// Accède aux paramètres de la modélisation
		std::array<Coordonnee::Angle, 3> const & taille_xyz() const;

		// Modélisation de la tete
		void contenu_liste() override;

	private:

		// Taille x et y de l'hélice
		std::array<Coordonnee::Angle, 3> _taille_xyz;
};

#endif // TETE_HH
