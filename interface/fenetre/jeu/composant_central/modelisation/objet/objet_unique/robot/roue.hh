#ifndef ROUE_HH
#define ROUE_HH

#include "../../objet_unique.hh"

// Roue d'un robot
class Roue:
	public Objet_unique
{
	public:

		// Instancie une roue avec une position et une orientation initiale
		Roue
		(
			std::array<Coordonnee::Distance, 3> const & position_xyz,
			std::array<Coordonnee::Angle, 3> const & orientation_xyz,
			Coordonnee::Distance const & diametre_xy,
			Coordonnee::Distance const & epaisseur_z
		);

		// Accède aux paramètres de la modélisation
		Coordonnee::Distance const & diametre_xy() const;
		Coordonnee::Distance const & epaisseur_z() const;

		// Modélisation de la roue
		void contenu_liste() override;

	private:

		// Diamètre de la roue
		Coordonnee::Distance _diametre_xy;

		// Epaisseur de la roue
		Coordonnee::Distance _epaisseur_z;
};

#endif // ROUE_HH
