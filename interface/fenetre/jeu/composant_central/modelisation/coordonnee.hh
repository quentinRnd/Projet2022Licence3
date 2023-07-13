#ifndef COORDONNEE_H
#define COORDONNEE_H

#include <QOpenGLFunctions>

#include <array>

// Coordonnée qui contient une dimension spatiale ou temporelle d'une modélisation OpenGL
namespace Coordonnee
{
	// La distance entre 2 points est représenté par un nombre réel
	using Distance = GLdouble;

	// Dégré d'un angle représenté par un nombre réel circonscrite dans l'interval de définition
	class Angle
	{
		public:

			// Instancie un angle null par défaut
			Angle();

			// Instancie une orientation avec une valeur
			Angle
			(
				GLdouble const & valeur
			);

			// Ajoute un angle
			Angle & operator+=(Angle const & angle);

			// Soustrait un angle
			Angle & operator-=(Angle const & angle);

			// Incrémente l'angle
			Angle & operator++();

			// Décrémente l'angle
			Angle & operator--();

			// Renvoie vrai si l'angle à opéré une révolution
			bool const & revolution() const;

			// Donne l'angle en radian
			GLdouble radian() const;

			// Convertion implicite de l'objet en nombre réel
			operator GLdouble () const;

		private:

			// Interval de définition
			static const GLdouble _minimum_revolution;
			static const GLdouble _maximum_revolution;

			// Retourne la valeur circonscrite de l'angle dans l'interval de définition
			static GLdouble circonscrit
			(
				GLdouble valeur
			);

			// Stocke la valeur de l'angle
			GLdouble _valeur;

			// L'angle à opéré une révolution
			bool _revolution;
	};

	// Quantité de temps en microsecondes entre 2 dates
	using Duree = std::chrono::microseconds;

	// Évenement temporel
	using Date = std::chrono::time_point<std::chrono::system_clock>;
}

#endif // COORDONNEE_H
