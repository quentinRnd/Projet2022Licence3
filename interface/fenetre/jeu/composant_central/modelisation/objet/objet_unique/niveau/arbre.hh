#ifndef ARBRE_H
#define ARBRE_H

#include "../../objet_unique.hh"

// Arbre du niveau 1
class Arbre:
    public Objet_unique
{
    public:

		Arbre
		(
		    std::array<Coordonnee::Distance, 3> const & position_xyz,
		    std::array<Coordonnee::Angle, 3> const & orientation_xyz,
			Coordonnee::Distance const & diametre_xz_tronc,
			Coordonnee::Distance const & taille_y_tronc,
			Coordonnee::Distance const & diametre_xyz_feuilles
		);

		// Accède aux paramètres de la modélisation
		Coordonnee::Distance const & diametre_xz_tronc() const;
		Coordonnee::Distance const & taille_y_tronc() const;
		Coordonnee::Distance const & diametre_xyz_feuilles() const;

		// Modélisation de l'arbre
		void contenu_liste() override;

    private:

		// Diamètre xz du tronc de l'arbre
		Coordonnee::Distance _diametre_xz_tronc;

		// Taille y du tronc de l'arbre
		Coordonnee::Distance _taille_y_tronc;

		// Diamètre xyz des feuilles de l'arbre
		Coordonnee::Distance _diametre_xyz_feuilles;
};

#endif // ARBRE_H
