#ifndef ATTACHE_ROUE_HH
#define ATTACHE_ROUE_HH

#include "../../objet_unique.hh"

// Attache une roue au corps du robot
class Attache_roue:
	public Objet_unique
{
	public:

		// Instancie l'attache d'une roue
		Attache_roue
		(
			std::array<Coordonnee::Distance, 3> const & position_xyz,
			std::array<Coordonnee::Angle, 3> const & orientation_xyz,
			std::array<Coordonnee::Angle, 2> const & taille_yz,
			Coordonnee::Distance const & diametre_tubes
		);

		// Accède aux paramètres de la modélisation
		std::array<Coordonnee::Angle, 2> const & taille_yz() const;
		Coordonnee::Distance const & diametre_tubes() const;

		// Modélisation de l'attache d'une rour
		void contenu_liste() override;

	private:

		// Taille yz de l'attache de roue
		std::array<Coordonnee::Angle, 2> _taille_yz;

		// Diamètre des tubes de l'attache de roue
		Coordonnee::Distance _diametre_tubes;
};

#endif // ATTACHE_ROUE_HH
