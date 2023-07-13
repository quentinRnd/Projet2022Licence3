#ifndef ROUTE_H
#define ROUTE_H

#include "../../objet_unique.hh"

// Segment de route dans un niveau
class Route:
    public Objet_unique
{
    public:

		Route
		(
		    std::array<Coordonnee::Distance, 3> const & position_xyz,
			std::array<Coordonnee::Angle, 3> const & orientation_xyz,
			Coordonnee::Distance const & taille_xz_sections,
			Coordonnee::Distance const & taille_y_sections,
			std::size_t const & nombre_sections,
			Coordonnee::Distance const & rayon_xy_ralentisseurs
		);

		// Accède aux paramètres de la modélisation
		Coordonnee::Distance const & taille_xz_sections() const;
		Coordonnee::Distance const & taille_y_sections() const;
		std::size_t const & nombre_sections() const;
		Coordonnee::Distance const & rayon_xy_ralentisseurs() const;

		// Modélisation du segment de route
		void contenu_liste() override;

	private:

		// Modélise un ralentisseur sur une section du segment de route
		void ralentisseur() const;

		// Taille xz des sections du segment de route
		Coordonnee::Distance _taille_xz_sections;

		// Taille y des sections du segment de route
		Coordonnee::Distance _taille_y_sections;

		// Nombre de sections du segment de route
		std::size_t  _nombre_sections;

		// Rayon xy des ralentisseurs qui délimitent les section du segment de route
		Coordonnee::Distance _rayon_xy_ralentisseurs;
};

#endif // ARBRE_H
