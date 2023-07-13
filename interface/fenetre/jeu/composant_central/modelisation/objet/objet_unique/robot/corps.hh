#ifndef CORPS_HH
#define CORPS_HH

#include "../../objet_unique.hh"

// Corps d'un robot
class Corps:
	public Objet_unique
{
	public:

		// Instancie un corps avec une position et une orientation initiale
		Corps
		(
			std::array<Coordonnee::Distance, 3> const & position_xyz,
			std::array<Coordonnee::Angle, 3> const & orientation_xyz,
			std::array<Coordonnee::Distance, 3> const & taille_xyz
		);

		// Accède aux paramètres de la modélisation
		std::array<Coordonnee::Distance, 3> const & taille_xyz() const;

		// Modélisation du corps
		void contenu_liste() override;

	private:

		// Taille du corps
		std::array<Coordonnee::Distance, 3> _taille_xyz;
};

#endif // CORPS_HH
