#ifndef POSITION_VALIDE_H
#define POSITION_VALIDE_H

#include "../../objet_unique.hh"

// Zone valide pour le robot
class Zone_valide:
    public Objet_unique
{
    public:

		// Instancie une position valide
		Zone_valide
		(
			std::array<Coordonnee::Distance, 3> const & position_xyz,
		    bool const & arrivee
		);

		// Acesseurs
		bool const & arrivee() const;

		// Détermine si une position est contenue dans la zone valide
		bool contenue(std::array<Coordonnee::Distance, 3> const & position_xyz);

		// Modélisation de la boîte de collision
		void contenu_liste() override;

    private:

		// Détermine si la zone valide est l'arrivée
		bool _arrivee;
};

#endif // POSITION_VALIDE_H
