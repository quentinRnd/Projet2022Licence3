#ifndef BUISSON_H
#define BUISSON_H

#include "../../objet_unique.hh"

// Buisson dans un niveau
class Buisson:
    public Objet_unique
{
    public:

		Buisson
		(
		    std::array<Coordonnee::Distance, 3> const & position_xyz,
			std::array<Coordonnee::Angle, 3> const & orientation_xyz,
			Coordonnee::Distance const & diametre_xyz
		);

		// Accède aux paramètres de la modélisation
		Coordonnee::Distance const & diametre_xyz() const;

		// Modélisation du buisson
		void contenu_liste() override;

	private:

		// Diamètre xyz du buisson
		Coordonnee::Distance _diametre_xyz;
};

#endif // BUISSON_H
