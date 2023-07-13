#ifndef HERBE_H
#define HERBE_H

#include "../../objet_unique.hh"

// Herbe dans un niveau
class Herbe:
    public Objet_unique
{
    public:

		Herbe
		(
		    std::array<Coordonnee::Distance, 3> const & position_xyz,
			std::array<Coordonnee::Angle, 3> const & orientation_xyz,
			std::array<Coordonnee::Distance, 3> const & taille_xyz
		);

		// Accède aux paramètres de la modélisation
		std::array<Coordonnee::Distance, 3> const & taille_xyz() const;

		// Modélisation de l'herbe
		void contenu_liste() override;

	private:

		// Taille xyz du pavé d'herbe
		std::array<Coordonnee::Distance, 3> _taille_xyz;
};

#endif // HERBE_H
