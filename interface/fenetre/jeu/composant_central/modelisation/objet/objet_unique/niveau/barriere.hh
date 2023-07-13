#ifndef BARRIERE_H
#define BARRIERE_H

#include "../../objet_unique.hh"

// Berriere dans un niveau
class Barriere:
    public Objet_unique
{
    public:

		Barriere
		(
		    std::array<Coordonnee::Distance, 3> const & position_xyz,
			std::array<Coordonnee::Angle, 3> const & orientation_xyz,
			Coordonnee::Distance const & taille_y,
			Coordonnee::Distance const & diametre_barres,
			Coordonnee::Distance const & taille_x_barres,
			std::size_t const & nombre_sections
		);

		// Accède aux paramètres de la modélisation
		Coordonnee::Distance const & taille_y() const;
		Coordonnee::Distance const & diametre_barres() const;
		Coordonnee::Distance const & taille_x_barres() const;
		std::size_t const & nombre_sections() const;

		// Modélisation de la barrière
		void contenu_liste() override;

	private:

		// Taille y de la barrière
		Coordonnee::Distance _taille_y;

		// Diamètre xyz de la barrière
		Coordonnee::Distance _diametre_barres;

		// Taille x des barres de la barrière
		Coordonnee::Distance _taille_x_barres;

		// Nombre de sections de la barrière
		std::size_t _nombre_sections;
};

#endif // BARRIERE_H
