#ifndef DRAPEAU_H
#define DRAPEAU_H

#include "../../objet_unique.hh"

// Drapeau dans un niveau
class Drapeau:
    public Objet_unique
{
    public:

		Drapeau
		(
		    std::array<Coordonnee::Distance, 3> const & position_xyz,
			std::array<Coordonnee::Angle, 3> const & orientation_xyz,
			std::array<Coordonnee::Distance, 3> const & taille_etoffe_xyz,
			Coordonnee::Distance const & diametre_xz_hampe,
			Coordonnee::Distance const & taille_y_hampe
		);

		// Accède aux paramètres de la modélisation
		std::array<Coordonnee::Distance, 3> const & taille_etoffe_xyz() const;
		Coordonnee::Distance const & diametre_xz_hampe() const;
		Coordonnee::Distance const & taille_y_hampe() const;

		// Modélisation du drapeau
		void contenu_liste() override;

	private:

		// Taille xyz de l'étoffe du drapeau
		std::array<Coordonnee::Distance, 3> _taille_etoffe_xyz;

		// Diamètre xz de la hampe du drapeau
		Coordonnee::Distance _diametre_xz_hampe;

		// Taille y de la hampe du drapeau
		Coordonnee::Distance _taille_y_hampe;
};

#endif // DRAPEAU_H
