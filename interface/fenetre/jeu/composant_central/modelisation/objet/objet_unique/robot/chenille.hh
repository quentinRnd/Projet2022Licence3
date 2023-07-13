#ifndef CHENILLE_HH
#define CHENILLE_HH

#include "../../objet_unique.hh"

// Chenille d'un robot
class Chenille:
	public Objet_unique
{
	public:

		// Instancie une chenille avec une position et une orientation initiale
		Chenille
		(
			std::array<Coordonnee::Distance, 3> const & position_xyz,
			std::array<Coordonnee::Angle, 3> const & orientation_xyz,
			Coordonnee::Distance const & taille_tube_haut_x,
			Coordonnee::Distance const & longueur_tube_milieu,
			Coordonnee::Distance const & taille_coins_xy,
			std::array<Coordonnee::Distance, 2> taille_tubes_yz
		);

		// Accède aux paramètres de la modélisation
		Coordonnee::Distance const & taille_tube_haut_x() const;
		Coordonnee::Distance const & longueur_tube_milieu() const;
		Coordonnee::Distance const & taille_coins_xy() const;
		std::array<Coordonnee::Distance, 2>  const & taille_tubes_yz() const;

		// Accède à des valeurs caluclées déduites des paramètres
		std::array<Coordonnee::Distance, 2> const & taille_tube_milieu_xy() const;
		Coordonnee::Distance const & taille_tube_bas_x() const;

		// Modélisation de la chenille
		void contenu_liste() override;

	private:

		// Taille x du tube en haut
		Coordonnee::Distance _taille_tube_haut_x;

		// Taille y de la chenille
		Coordonnee::Distance _longueur_tube_milieu;

		// Taille xy de coins de la chenille
		Coordonnee::Distance _taille_coins_xy;

		// Taille y et z des tubes
		std::array<Coordonnee::Distance, 2> _taille_tubes_yz;

		// Taille xy du tube au mileu
		std::array<Coordonnee::Distance, 2> _taille_tube_milieu_xy;

		// Taille x du tube en bas
		Coordonnee::Distance _taille_tube_bas_x;
};

#endif // CHENILLE_HH
