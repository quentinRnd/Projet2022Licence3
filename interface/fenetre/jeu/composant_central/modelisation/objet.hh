#ifndef OBJET_HH
#define OBJET_HH

#include <QOpenGLFunctions>

#include "coordonnee.hh"

// Objet présent dans une modélisation
class Objet:
	protected QOpenGLFunctions
{
	public:

		// Instancie un objet avec une position et une orientation initiale
		Objet
		(
			std::array<Coordonnee::Distance, 3> const & position_xyz,
			std::array<Coordonnee::Angle, 3> const & orientation_xyz
		);

		// Accède à la position et à l'orientation de l'objet
		std::array<Coordonnee::Distance, 3> const & position_xyz() const;
		std::array<Coordonnee::Angle, 3> const & orientation_xyz() const;

		// Mutateurs
		void position_xyz(std::array<Coordonnee::Distance, 3> const & position);
		void orientation_xyz(std::array<Coordonnee::Angle, 3> const & orientation);

		// Reinitialise les paramètres de l'objet
		virtual void reinitialise_parametres();

		// Initialise la modélisation de l'objet
		virtual void initialise_modelisation() = 0;

		// Modélise L'objet
		virtual void modelise() = 0;

	protected:

		// Positionne et oriente la modélisation de l'objet
		void positionne_oriente() const;

		// Position de l'objet
		std::array<Coordonnee::Distance, 3> _position_xyz;

		// Orientation de l'objet
		std::array<Coordonnee::Angle, 3> _orientation_xyz;

		// Position initiale de l'objet
		std::array<Coordonnee::Distance, 3> _position_xyz_initiale;

		// Orientation initiale de l'objet
		std::array<Coordonnee::Angle, 3> _orientation_xyz_initiale;
};

#endif // OBJET_HH
